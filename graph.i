%module graph
%include "std_string.i"
%include <std_shared_ptr.i>
%include "typemaps.i"


#include "libgraph.h"

%{
#include "libgraph.h"
using namespace gcalc;
%}

Graph create();

