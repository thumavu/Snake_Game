FROM alpine AS base

WORKDIR /snake

RUN apk update --no-cache && \
    apk add git g++ ncurses-dev ncurses-static

RUN git clone https://github.com/thumavu/Snake_Game.git .

RUN g++ main.cpp snake.class.cpp -o snake -lncurses

FROM alpine

LABEL org.opencontainers.image.authors="Thulasizwe Mavuso" \
    org.opencontainers.image.description="Snake game built with c++"

RUN apk update --no-cache && apk add g++ ncurses-terminfo-base ncurses-libs && \
    adduser -g "Thulasizwe Mavuso" -s /usr/sbin/nologin -D -H thulasizwe

COPY --from=base /snake/snake /snake

USER thulasizwe
CMD [ "./snake" ]