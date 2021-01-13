package ppgia.ms;

simple Server {
    parameters:
        @display("i=device/mainframe");
        int queueCapacity = default(0);
        double delay = default(0.3);
    gates:
        input in;
}