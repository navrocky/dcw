# Docker Compose Workspace manager

It helps to manage developer test environments based on docker-compose files.

## Installation

The released binaries are statically compiled, so they can run in almost all linux distributions, tested in Ubuntu 4 (2006). 
Supported platforms is:

* Linux x86, x86_64

To install `dcw` system wide and bash completion run this command in your terminal:

```sh
sudo sh -c 'curl -sSL https://github.com/navrocky/dcw/raw/master/install.sh | bash'
```

## Usage 

```
Usage: dcw [OPTIONS] SUBCOMMAND

Options:
  -h,--help                   Print this help message and exit

Subcommands:
  add, a                      Add named docker compose file as workspace
  rm, r                       Remove workspace
  list, l                     List registered workspaces
  up, u                       Switch to the workspace
  down, d                     Down current workspace
```

## Examples

### Add workspace:

```sh
dcw add myproj /home/user/myproj/docker-compose.yml
```

### List workspaces and view active:

```sh
dcw list
```

Output is:
```
🟢 myproj: /home/user/myproj/docker-compose.yml
⚫ otherproj: /home/user/otherproj/docker-compose.yml
```

### Switch to workspace

```sh
dcw up otherproj
```

### Stop workspace and optionally purge workspace data (volumes)

```sh
dcw down -p
```
