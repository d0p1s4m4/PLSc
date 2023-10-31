GIT	:= git

git_tag := $(shell git describe --abbrev=4 --match='v[0-9]*' HEAD 2)
ifneq ($(.SHELLSTATUS), 0)
git_tag := v0.0.0
endif

git_commit := $(shell git rev-parse --short HEAD)

ifneq ($(RUNNER_OS),)
VERSION := $(git_tag)-$(RUNNER_OS)
else
VERSION := $(git_tag)
endif

ifneq ($(OS),Windows_NT)

git_status := $(shell git status)
ifneq ($(git_status),)
git_dirty	= -dirty
endif

endif

VERSION_STR :=\"$(VERSION)-$(git_commit)$(git_dirty)\"
