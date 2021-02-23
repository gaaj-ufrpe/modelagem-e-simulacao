network Graph
{
    parameters:
        int nnodes = default(3); 
    submodules:
        source: Source;
        sink: Sink;
        nodes[nnodes]: Node;
    connections:
        source.out++ --> Edge{ distance=1; } --> nodes[0].in++;
        nodes[0].out++ --> Edge{ distance=2; } --> nodes[1].in++;
        nodes[0].out++ --> Edge{ distance=3; special=true; @display("ls=green"); } --> nodes[2].in++;
        nodes[1].out++ --> Edge{ distance=2; } --> nodes[2].in++;
        nodes[2].out++ --> Edge{ distance=1; } --> sink.in++;
}