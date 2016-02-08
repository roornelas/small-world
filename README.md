# Small World Phenomenon

Based on Jon Kleinberg's [The Small World Phenomenon: An Algorithmic Perspective](https://www.cs.cornell.edu/home/kleinber/swn.pdf), this repo builds out the tools that we need to create graphs that model human networks and test different kinds of searches to actually find the expected short paths between people that are geographically distant. The repo does 2 main things:

1. Build a way to randomly generate graphs that are like the the kinds we would see humans in
2. Compare the actual shortest path between any 2 people to both random walks and Kleinberg's Greedy Algorithm - the latter of which models how humans actually make decisions in real life.

## Core Idea

The main Idea that Kleinberg suggests is that human networks of the kind we see in real life can be randomly generated, but only in a very specific manner. The main parameters of this model are:

1. The number of local connections each person has
2. The number of long range connections each person has
3. The tendency long range connections have to be closer, or further away from the source

He finds, that for a 2-dimensional network of people, there is only one value for parameter 3 that allows for people to be able to find a short path from them to a geographically distant person.

## Applications

This makes it easy to both model graphs that represent human networks laid out geographically and to search actual graphs in a manner that matches how people would do so at an individual level. This algorithm could be used, for example, in something like [searching Facebook's graph to see how connected people are](https://research.facebook.com/blog/three-and-a-half-degrees-of-separation/).
