.PHONY: all clean debug release-armv7 run 
SOURCE_DIR:=${CURDIR}
CARGO:=cargo
DOCKER=docker

all: debug

run:
	${CARGO} run -- --config=${SOURCE_DIR}/etc/tglight.toml ${TGLIGHT_FLAGS}

clean: 
	${CARGO} clean

debug: 
	${CARGO} build

release-armv7:
	${CARGO} build --target=armv7-unknown-linux-gnueabihf --release

setup: 
	@if [ -z ${TGLIGHT_HOST} ]; then echo "Please set TGLIGHT_HOST environment variable" && exit 255; fi
	cat ${HOME}/.ssh/id_rsa.pub | ssh pi@${TGLIGHT_HOST} 'sudo mount -o remount,rw / && mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys'
	ssh pi@${TGLIGHT_HOST} 'sudo mkdir -p /root/.ssh && sudo cp /home/pi/.ssh/authorized_keys /root/.ssh/authorized_keys'

deploy: release-armv7
	@if [ -z ${TGLIGHT_HOST} ]; then echo "Please set TGLIGHT_HOST environment variable" && exit 255; fi
	@if [ -z ${CARGO_TARGET_DIR} ]; then echo "Please set CARGO_TARGET_DIR environment variable" && exit -1; fi
	-ssh root@${TGLIGHT_HOST} "service tglight stop"
	ssh pi@${TGLIGHT_HOST} "sudo mount -o remount,rw /"
	ssh root@${TGLIGHT_HOST} "mkdir -p /opt/tglight/bin"	
	scp ${CARGO_TARGET_DIR}/armv7-unknown-linux-gnueabihf/release/tglight root@${TGLIGHT_HOST}:/opt/tglight/bin/tglight
	ssh root@${TGLIGHT_HOST} "service tglight restart"
	-ssh root@${TGLIGHT_HOST} "sudo reboot"

docker-build:
	${DOCKER} build -t tglight .

docker-run: docker-build
	${DOCKER} run -it --rm -p 8080:8080 tglight

docker-deploy: docker-build
	@if [ -z ${TGLIGHT_HOST} ]; then echo "Please set TGLIGHT_HOST environment variable" && exit 255; fi
	${DOCKER} run -it --rm  -e "TGLIGHT_HOST=${TGLIGHT_HOST}" tglight deploy

docker-shell: 
	${DOCKER} run -it --rm -v${SOURCE_DIR}:/workdir --entrypoint=/bin/bash tglight
