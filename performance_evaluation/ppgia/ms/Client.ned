package ppgia.ms;

simple Client {
    parameters:
        @display("i=device/laptop");
        double delay = default(0.1);
    gates:
        output out;
}