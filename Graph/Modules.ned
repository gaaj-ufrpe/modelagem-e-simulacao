channel Edge {
    parameters:
        @display("ls=black,3");
        double distance = default(0.0);
        bool special = default(false);
}

simple Source
{
    parameters:
        @display("i=misc/node");
        double delay = default(1.0);
    gates:
        output out[];
}

simple Sink
{
    parameters:
        @signal[pathDistance](type=double);
        @signal[regularPathDistance](type=double);
        @signal[specialPathDistance](type=double);
        @signal[pathDelay](type=double);
        @signal[regularPathDelay](type=double);
        @signal[specialPathDelay](type=double);
        @statistic[pathDistance](title="Path Distance";record=mean,max,vector?; unit=s);
        @statistic[regularPathDistance](title="Regular Path Distance";record=mean,max,vector?; unit=s);
        @statistic[specialPathDistance](title="Special Path Distance";record=mean,max,vector?; unit=s);
        @statistic[pathDelay](title="Path Delay";record=mean,max,vector?; unit=s);
        @statistic[regularPathDelay](title="Regular Path Delay";record=mean,max,vector?; unit=s);
        @statistic[specialPathDelay](title="Special Path Delay";record=mean,max,vector?; unit=s);
        
        @display("i=misc/node2");
    gates:
        input in[];
}

simple Node
{
    parameters:
        @display("i=block/process");

    gates:
        input in[];
        output out[];
}


