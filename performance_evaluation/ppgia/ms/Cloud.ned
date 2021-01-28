package ppgia.ms;

module Cloud {
    parameters:
        @display("i=misc/cloud");
        int nservers = default(6);
    gates:
        input in[];
    submodules:
        loadBalancer: LoadBalancer;
        server[nservers]: Server;
    connections:
        for i=0..(sizeof(in)-1) {
        	in[i] --> loadBalancer.in++;
        }
        for i=0..(nservers-1) {
        	loadBalancer.out++ --> Ethernet100 --> server[i].in;
        }
}