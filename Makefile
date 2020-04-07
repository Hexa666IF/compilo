default: build

build:
	cd ./compiler && sh ./compile_if.sh

build-docker:
	cd ./compiler && sh ./compile_docker.sh

test:
	cd ./tests && sh ./test_if.sh

test-docker:
	cd ./tests && sh ./test.sh

build-test: build test

build-test-docker: build-docker test-docker