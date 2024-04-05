#!/bin/bash

set -e
set -x

curl -L https://github.com/navrocky/dcw/releases/download/1.0.0/dcw -o /usr/local/bin/dcw
chmod +x /usr/local/bin/dcw
curl -L https://github.com/navrocky/dcw/raw/master/completion.bash -o /etc/bash_completion.d/dcw_completion.bash

echo "== Installation completed successfully =="
