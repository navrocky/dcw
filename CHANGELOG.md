# 1.2.3 (2024.12.20)

* Pack binary with UPX

# 1.2.2 (2024.10.31)

* Fix removing of current workspace if compose file does not exists

# 1.2.1 (2024.09.17)

* Add `--build` parameter to compose up command

# 1.2.0 (2024.05.08)

* Switch to new command line parser [CLI11](https://github.com/CLIUtils/CLI11)
* Suggest workspace name in `up` command if it not provided. Name suggested if current directory matches workspace or 
  try to up the latest active workspace.
* Added shortcuts for all commands
* `dcw` without args shows a list of all workspaces

# 1.1.2 (2024.04.24)

* Fix location of state yaml file to `~/.local/share/dcw/state.yml`

# 1.1.1 (2024.04.09)

* Fix work dir when running `docker compose`

# 1.1.0 (2024.04.05)

* Add bash completion
* Add installation script
* Support for `docker compose` command
* Terminate partially started containers if the entire workspace cannot be started

# 1.0.0 (2024.04.04)

* Initial release
