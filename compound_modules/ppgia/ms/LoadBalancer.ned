package ppgia.ms;

simple LoadBalancer {
    parameters:
        @display("i=abstract/router");
        int queueCapacity = default(0);
        double delay = default(0.1);
    gates:
	    input in[];    
	    output out[];    
}