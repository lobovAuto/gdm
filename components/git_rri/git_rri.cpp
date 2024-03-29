#include "git_rri.hpp"

int git_libgit2_init();

GitRri::GitRri(/* args */)
{
}

GitRri::~GitRri()
{
}

int GitRri::push() {
    // git_libgit2_init();
    return 0;
}
int GitRri::pull() {
    return 0;
}
int GitRri::check_repo_to_gdm_files() {
    return 0;
}
int GitRri::checkout() {
    return 0;
}
int GitRri::status() {
    return 0;
}
int GitRri::clone() {
    git_libgit2_init();
    git_repository * repo = nullptr;
    const char url[]{"ssh://git@git.redpioneer.ru:2224/tools/dbc_agent.git"};
    const char path[]{"./tools/dbc_agent"};
    git_clone_options clone_opts = GIT_CLONE_OPTIONS_INIT;
	git_checkout_options checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

    checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;
	checkout_opts.progress_cb = nullptr;
	checkout_opts.progress_payload = nullptr;
	clone_opts.checkout_opts = checkout_opts;
	clone_opts.fetch_opts.callbacks.sideband_progress = nullptr;
	clone_opts.fetch_opts.callbacks.transfer_progress = nullptr;
	clone_opts.fetch_opts.callbacks.credentials = nullptr;
	clone_opts.fetch_opts.callbacks.payload = nullptr;


    git_clone(&repo, url, path, &clone_opts);
    return 0;
}