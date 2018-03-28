#!/bin/sh

d_start() {
    docker stop $(docker ps -a -q)
    cd docker-iot-secu
    docker-compose down
    docker-compose build
    docker-compose up -d
    cd ..
    if [ "$1" = "open" ]; then
        open http://iot-secu.localhost
        open http://iot-secu.localhost:8080
    fi
}

d_stop() {
    cd docker-iot-secu
    docker-compose stop
    cd ..
}

case "$1" in
    init)
        key="iot-secu.localhost"
        if grep -q $key /private/etc/hosts; then
            echo "Already in host file"
        else
            echo "0.0.0.0  $key" >> /private/etc/hosts
            echo "Added in host file"
        fi
        d_start $2
        ;;

    start|stop)
        d_${1} $2
        ;;

    restart)
        d_stop
        d_start
        ;;

    *)
	    echo "Usage: $0 init(open)|start(open)|stop|restart"
		            exit 1

esac
exit 0
