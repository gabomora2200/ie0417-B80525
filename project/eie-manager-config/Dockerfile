# Docker file used to build eie_manager_config image

FROM ubuntu:latest as base


# Install base system software
RUN apt-get update && apt-get --yes --no-install-recommends install \
        curl git locales sudo iproute2 locales

# Set the locale
ENV LANG en_US.UTF-8
RUN locale-gen en_US.UTF-8 && update-locale LANG=en_US.UTF-8

# Install developer tools
RUN apt-get update && apt-get --yes --no-install-recommends install \
    python3 python3-setuptools python3-pip 

# Install Package in the system
COPY . /src_code
RUN python3 -m pip install /src_code
RUN rm -rf /src_code

