# Docker Compose Workspace manager

It helps to manage developer test environments based on docker-compose files.

## Installation

Supported platforms:

* Linux x86, x86_64

To install `dcw` run this command in your terminal:

```sh
sudo sh -c 'curl -sSL https://github.com/navrocky/dcw/raw/master/install.sh | bash'
```

## Usage 

```
USAGE: dcw <command> <options> 

  add <name> <compose file> Add named docker compose file as workspace 
  down                      Down current workspace 
  list                      List registered workspaces 
  rm <name>                 Remove workspace by name 
  up <name>                 Switch to the workspace with a name 

OPTIONAL:
 -h, --help <arg> Print this help.
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
