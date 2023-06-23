GIT	:= git

git_tag := $(shell git describe --abbrev=4 --match='v[0-9]*' HEAD 2)
ifneq ($(.SHELLSTATUS), 0)
git_tag := v0.0
endif

git_commit := $(shell git rev-parse --short HEAD)

git_status := $(shell git status)

VERSION := $(git_tag)-$(git_commit)

ifneq ($(git_status),)
VERSION	+= (dirty)
endif

VERSION_STR :="\"$(VERSION)\""
