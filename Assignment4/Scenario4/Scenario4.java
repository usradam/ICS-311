/*****************************************************************
 //
 //  NAMES:       Adam Graham, Shayde Tamura, Sam Doan
 //
 //  Assignment:  4
 //
 //  CLASS:       ICS 311
 //
 //  INSTRUCTOR:  Brook Conner
 //
 //  DATE:        July 16, 2024
 //
 //  FILE:        Scenario4.java
 //
 //  DESCRIPTION:
 //   A program that finds the shortest path to a specified island when given a starting point from
 //   within the Polynesian Triangle.
 //
 ****************************************************************/

import java.util.*;
import java.util.stream.Collectors;

public class Scenario4 {

    static class Island {
        String name;
        int experienceTime;    // Minutes
        List<Edge> edges;

        public Island(String name, int experienceTime) {
            this.name = name;
            this.experienceTime = experienceTime;
            this.edges = new ArrayList<>();
        }
    }

    static class Edge {
        Island place;
        int travelTime;    // Minutes

        public Edge(Island place, int travelTime) {
            this.place = place;
            this.travelTime = travelTime;
        }
    }

    public static class PolynesianTriangle {
        List<Island> islands;

        public PolynesianTriangle() {
            this.islands = new ArrayList<>();
        }

        public void addIsland(Island island) {
            this.islands.add(island);
        }

        public void addEdge(Island source, Island place, int travelTime) {
            source.edges.add(new Edge(place, travelTime));
        }

        public void dijkstra(Island start) {
            Map<Island, Integer> distances = new HashMap<>();
            Map<Island, Island> predecessor = new HashMap<>();
            PriorityQueue<Island> pq = new PriorityQueue<>(Comparator.comparing(distances::get));

            for (Island island : islands) {
                if (island == start) {
                    distances.put(island, 0);
                }
                else {
                    distances.put(island, Integer.MAX_VALUE);
                }
                pq.add(island);
            }

            while (!pq.isEmpty()) {
                Island current = pq.poll();

                for (Edge edge : current.edges) {
                    Island neighbor = edge.place;
                    int newDistance = distances.get(current) + edge.travelTime + neighbor.experienceTime;

                    if (newDistance < distances.get(neighbor)) {
                        pq.remove(neighbor);
                        distances.put(neighbor, newDistance);
                        predecessor.put(neighbor, current);
                        pq.add(neighbor);
                    }
                }
            }

            // Print the path from the start node to itself
            System.out.println("Path to " + start.name + ": " + start.name);

            // Print the paths to the other islands
            for (Island island : islands) {
                if (island != start) {
                    List<Island> path = new ArrayList<>();
                    for (Island at = island; at != null; at = predecessor.get(at)) {
                        path.add(at);
                    }
                    Collections.reverse(path);
                    System.out.println("Path to " + island.name + ": " + path.stream().map(i -> i.name).collect(Collectors.joining(" -> ")));
                }
            }
        }
    }

    public static void main(String[] args) {
        PolynesianTriangle triangle = new PolynesianTriangle();

        Island hawaii = new Island("Hawaii", 120);
        Island newZealand = new Island("New Zealand", 180);
        Island easterIsland = new Island("Easter Island", 150);
        Island tahiti = new Island("Tahiti", 90);
        Island samoa = new Island("Samoa", 110);

        triangle.addIsland(hawaii);
        triangle.addIsland(newZealand);
        triangle.addIsland(easterIsland);
        triangle.addIsland(tahiti);
        triangle.addIsland(samoa);

        triangle.addEdge(hawaii, tahiti, 300);
        triangle.addEdge(tahiti, hawaii, 280);
        triangle.addEdge(tahiti, newZealand, 600);
        triangle.addEdge(newZealand, tahiti, 580);
        triangle.addEdge(tahiti, easterIsland, 400);
        triangle.addEdge(easterIsland, tahiti, 380);
        triangle.addEdge(tahiti, samoa, 200);
        triangle.addEdge(samoa, tahiti, 180);

        System.out.println("When the source node (starting point) is Hawaii:");
        triangle.dijkstra(hawaii);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source node (starting point) is New Zealand:");
        triangle.dijkstra(newZealand);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source node (starting point) is Easter Island:");
        triangle.dijkstra(easterIsland);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source node (starting point) is Tahiti:");
        triangle.dijkstra(tahiti);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source node (starting point) is Samoa:");
        triangle.dijkstra(samoa);
    }
}
