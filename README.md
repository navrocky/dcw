# Docker Compose Workspace manager

It helps to manage developer test environments based on docker-compose files.

## Installation

Supported platforms:

* Linux x86, x86_64

To install `dcw` run this command in your terminal:

```sh
curl https://github.com/navrocky/dcw/releases/download/1.0.0/dcw-Lo /usr/local/bin/dcw
chmod +x /usr/local/bin/dcw
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
