#include "clar_libgit2.h"
#include "buffer.h"
#include "posix.h"

static git_repository *repo;

void test_repo_setters__initialize(void)
{
	cl_fixture_sandbox("testrepo.git");
	cl_git_pass(git_repository_open(&repo, "testrepo.git"));
	cl_must_pass(p_mkdir("new_workdir", 0777));
}

void test_repo_setters__cleanup(void)
{
	git_repository_free(repo);
	cl_fixture_cleanup("testrepo.git");
	cl_must_pass(p_rmdir("new_workdir"));
}

void test_repo_setters__setting_a_workdir_turns_a_bare_repository_into_a_standard_one(void)
{
	cl_assert(git_repository_is_bare(repo) == 1);

	cl_assert(git_repository_workdir(repo) == NULL);
	cl_git_pass(git_repository_set_workdir(repo, "./new_workdir"));

	cl_assert(git_repository_workdir(repo) != NULL);
	cl_assert(git_repository_is_bare(repo) == 0);
}

void test_repo_setters__setting_a_workdir_prettifies_its_path(void)
{
	cl_git_pass(git_repository_set_workdir(repo, "./new_workdir"));

	cl_assert(git__suffixcmp(git_repository_workdir(repo), "/") == 0);
}