package ppgia.ms;

simple LoadBalancer {
    parameters:
        @group(LoadBalancer);
        @signal[dropped](type="long");
        @signal[busy](type="long");
        @signal[queueLength](type="long");
        @statistic[dropped](title="Dropped jobs";record=count,timeavg,vector;interpolationmode=none; unit=ms);
        @statistic[busy](title="Busy";record=timeavg,max,vector;interpolationmode=none; unit=ms);
        @statistic[queueLength](title="Queue length";record=mean,timeavg,max,vector;interpolationmode=none; unit=ms);
        
        @display("i=abstract/router");
        int queueCapacity = default(50);
        double delay = default(0.005);
    gates:
	    input in[];    
	    output out[];    
}