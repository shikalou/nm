FROM	debian:buster

RUN		apt-get update -y && apt-get upgrade -y

RUN		apt-get install sudo vim wget clang make gcc -y

COPY	../ ./nm
