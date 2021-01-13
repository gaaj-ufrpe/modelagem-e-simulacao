package ppgia.ms;

simple Client {
    parameters:
        @display("i=device/laptop");
        double delay = default(0.95);
    gates:
        output out;
}