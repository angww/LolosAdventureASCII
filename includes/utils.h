

void setCharAt(char ch, int x, int y) {
    locate(x, y);
    setChar(ch);
}

void setStringAt(RLUTIL_STRING_T str, int x, int y) {
    locate(x, y);
    setString(str);
}

void regua80() {
    printf("123456789|123456789|123456789|123456789|123456789|123456789|123456789|123456789| <-80\n");
}