# explain why need editor

explain why

explain the relation between editor and engine


# design editor

## border

analyze border:
how can user use it?

give image (draft image with only one "start" button)

start/stop button + canvas


package editor to one dist file;
import it in html page;



## whether to use redux

discuss: global data(store) vs local data(state)


only use global data, no local data?


## design data


state:

ui state(redux store)

engine state



////note: no editor state!!!!

still need editor state for not show data(which not affect ui)!!!
(
by dicuss "where to store loopId" and avoid re-render!
)


why?
no need to update All, Inspector, ...
just update ui state->all, inspector state, ...



need extract ui data from engine state to ui state!


should update engine state and ui state in store->reducer?


## import engine

use adapter

invoke engine file according to namespace
(work by es6 module)

