FROM gcc:4.9
COPY .. /usr/prim/
WORKDIR /usr/prim/
LABEL name="Prim, environnement line"
LABEL version="1.0"
LABEL description="This is a game where you manage a production chain to close the gate \
    between two ENSIIE. Game requested by Dimitri WATEL."
RUN make
CMD ["./bin/prim"]