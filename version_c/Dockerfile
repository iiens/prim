#
# Prim docker launcher
#
# Can be launched build then launched using
# - docker build -t prim:latest .
# - docker run -it prim
#
FROM gcc:8.4
COPY . /usr/prim/
WORKDIR /usr/prim/
LABEL name="Prim, environment line"
LABEL version="1.0"
LABEL description="This is a game where you manage a production chain to close the gate \
    between two ENSIIE. Game requested by Dimitri WATEL."
# make program
RUN make

## locale
RUN apt-get clean && apt-get update && apt-get install -y locales
RUN localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG=en_US.UTF-8
ENV LANGUAGE=en_US.UTF-8
ENV LC_ALL=C

#
## texlive-fonts-recommended
#RUN apt-get clean && apt-get update && apt-get install -y fonts-lato lmodern ttf-bitstream-vera
#RUN apt-get clean && apt-get update && apt-get install -y fonts-dejavu fonts-mathjax fonts-lyx fonts-font-awesome fonts-roboto
#RUN apt-get clean && apt-get update && apt-get install -y fonts-glyphicons-halflings texlive-fonts-recommended
#RUN apt-get clean && apt-get update && apt-get install -y ttf-ancient-fonts ttf-unifont ttf-bitstream-vera
#RUN apt-get clean && apt-get update && apt-get install -y xfonts-unifont ttf-unifont gucharmap

# download packages
#RUN apt-get clean && apt-get update && apt-get install -y locales ttf-ancient-fonts ttf-unifont ttf-bitstream-vera
#RUN apt-get clean && apt-get update && apt-get install -y texlive-fonts-recommende fonts-noto xfonts-unifont ttf-unifont
#RUN apt-get clean && apt-get update && apt-get install -y gucharmap
## moar
#RUN apt-get clean && apt-get update && apt-get install -y fonts-lato fonts-dejavu fonts-ipafont-gothic fonts-mathjax
# start
CMD ["./bin/prim"]