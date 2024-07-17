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
 //  FILE:        Scenario1.java
 //
 //  DESCRIPTION:
 //   A program that finds a path to all of the islands, while taking into consideration the population of the island and how recent
 //   the previous visit was. 
 //
 //
 ****************************************************************/
import java.util.*;
import java.util.stream.Collectors;

public class Scenario1 {

    static class Island {
        String name;
        int experienceTime; // Time required to share skills in minutes
        int population;     // Population of the island
        List<Edge> edges;
        long lastVisitTime; // Time of the last visit in milliseconds since epoch

        public Island(String name, int experienceTime, int population) {
            this.name = name;
            this.experienceTime = experienceTime;
            this.population = population;
            this.edges = new ArrayList<>();
            this.lastVisitTime = 0; // Initialize last visit time to zero (indicating no visit yet)
        }
    }

    static class Edge {
        Island destination;
        int travelTime; // Travel time in minutes

        public Edge(Island destination, int travelTime) {
            this.destination = destination;
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

        public void addEdge(Island source, Island destination, int travelTime) {
            source.edges.add(new Edge(destination, travelTime));
        }

        public void dijkstra(Island start) {
            Map<Island, Double> priorityScores = new HashMap<>();
            Map<Island, Island> predecessor = new HashMap<>();
            PriorityQueue<Island> pq = new PriorityQueue<>(Comparator.comparing(priorityScores::get));
            long currentTime = System.currentTimeMillis();

            for (Island island : islands) {
                if (island == start) {
                    priorityScores.put(island, 0.0);
                } else {
                    priorityScores.put(island, Double.MAX_VALUE);
                }
                pq.add(island);
            }

            while (!pq.isEmpty()) {
                Island current = pq.poll();

                for (Edge edge : current.edges) {
                    Island neighbor = edge.destination;
                    double travelDistance = edge.travelTime;
                    double recencyFactor = (currentTime - neighbor.lastVisitTime) / 1000.0; // recency in seconds
                    double populationFactor = Math.log(neighbor.population);
                    double newPriority = priorityScores.get(current) + travelDistance + neighbor.experienceTime + recencyFactor - populationFactor;

                    if (newPriority < priorityScores.get(neighbor)) {
                        pq.remove(neighbor);
                        priorityScores.put(neighbor, newPriority);
                        predecessor.put(neighbor, current);
                        pq.add(neighbor);
                    }
                }
            }

            // Print the path from the start island to itself
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

            // Update last visit time for each island
            for (Island island : islands) {
                if (priorityScores.get(island) != Double.MAX_VALUE) {
                    island.lastVisitTime = currentTime;
                }
            }
        }
    }

    public static void main(String[] args) {
        PolynesianTriangle triangle = new PolynesianTriangle();

        Island hawaii = new Island("Hawaii", 120, 1400000);
        Island newZealand = new Island("New Zealand", 180, 4900000);
        Island easterIsland = new Island("Easter Island", 150, 7800);
        Island tahiti = new Island("Tahiti", 90, 183500);
        Island samoa = new Island("Samoa", 110, 198000);

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

        System.out.println("When the source island is Hawaii:");
        triangle.dijkstra(hawaii);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source island is New Zealand:");
        triangle.dijkstra(newZealand);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source island is Easter Island:");
        triangle.dijkstra(easterIsland);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source island is Tahiti:");
        triangle.dijkstra(tahiti);
        System.out.println("----------------------------------------------------------------");

        System.out.println("When the source island is Samoa:");
        triangle.dijkstra(samoa);
    }
}
