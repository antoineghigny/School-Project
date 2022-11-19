package esi.atl.g56359.stibride.model;

import esi.atl.g56359.stibride.model.dto.FavoriteDto;
import esi.atl.g56359.stibride.model.dto.StationDto;
import esi.atl.g56359.stibride.model.dto.StopDto;
import esi.atl.g56359.stibride.model.repository.FavoriteRepository;
import esi.atl.g56359.stibride.model.repository.StopRepository;
import esi.atl.g56359.stibride.model.utils.GameState;
import esi.atl.g56359.stibride.model.utils.LangState;
import esi.atl.g56359.stibride.model.utils.RepositoryException;
import esi.atl.g56359.stibride.model.utils.graph.Dijkstra;
import esi.atl.g56359.stibride.model.utils.graph.Graph;
import esi.atl.g56359.stibride.model.utils.graph.Node;
import esi.atl.g56359.stibride.model.utils.observer.Observable;
import esi.atl.g56359.stibride.model.utils.observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.ObservableSet;

import java.util.*;
import java.util.stream.Collectors;

public class Model implements Observer, Observable {
    public static final String INVALID_DATA = "invalidData";
    public static final String FAVORITE_DELETE_FAIL = "deleteFail";
    public static final String FAVORITE_ADD_FAIL_MAX = "maxFavorite";
    public static final String FAVORITE_REPO_ERROR = "repoError";
    public static final String FAVORITE_UPDATE_NO_CHANGES = "updateNoChanges";

    private final ObservableList<StationDto> pathStations = FXCollections.observableArrayList();
    private final ObservableSet<StationDto> allStations = FXCollections.observableSet();
    private final ObservableSet<FavoriteDto> allFavorites = FXCollections.observableSet();
    private final StopRepository repository = new StopRepository();
    private final FavoriteRepository favoriteRepository = new FavoriteRepository();

    private final HashMap<Integer, Node> allNodeStations = new HashMap<>();
    private Graph graph;
    private boolean isDoneSearch = false;
    private String msgFavorite = null;

    private StationDto currentSource;
    private StationDto destinationSource;

    private ArrayList<Observer> observers;

    public Model() throws RepositoryException {
        this.observers = new ArrayList<>();
        repository.getAll().forEach(dto -> allStations.add(dto.getStation()));
        resetFavorite();
    }


    /**
     * It clears the list of favorites and then adds all the favorites from the repository
     */
    private void resetFavorite() throws RepositoryException {
        System.out.println("reset favorite");
        allFavorites.clear();
        allFavorites.addAll(favoriteRepository.getAll());
    }

    /**
     * For each station, get all the stops that are in the same station, get all the stops that are adjacent to those
     * stops, and add those adjacent stops to the graph
     */
    private void makeGraph() throws RepositoryException {
        graph = new Graph();
        List<StopDto> allStops = null;
        List<StopDto> adjStops;

        allStations.forEach(station -> {
            allNodeStations.put(station.getKey(), new Node(station));
        });

        for (StationDto station : allStations) {
            allStops = repository.getSame(station.getKey());

            Set<Integer> stopLines = allStops.stream().map(StopDto::getLine).collect(Collectors.toSet());
            station.setLines(stopLines);

            adjStops = repository.getAdj(allStops);

            // Change the distance between stations here
            adjStops.forEach(stops -> allNodeStations.get(station.getKey()).addDestination(allNodeStations.get(stops.getStation().getKey()), 1));
        }

        allNodeStations.forEach((key, value) -> graph.addNode(value));
    }

    /**
     * Calculate the shortest path from the source to the destination and notify the observers
     *
     * @param source      The source station.
     * @param destination The destination station.
     */
    public void search(StationDto source, StationDto destination) throws RepositoryException {
        new Thread(() -> {
            try {
                makeGraph();
            } catch (RepositoryException e) {
                e.printStackTrace();
            }

            if (source == null || destination == null) {
                isDoneSearch = false;
                notifyObservers();
                return;
            }
            pathStations.clear();
            // Calculating the shortest path from the source to the destination.
            Graph shortestGraph = Dijkstra.calculateShortestPathFromSource(graph, allNodeStations.get(source.getKey()));

            // Getting the shortest path from the source to the destination.
            shortestGraph.getNodes().stream().filter(node -> node.getStation().getKey().equals(destination.getKey()))
                    .flatMap(node -> node.getShortestPath().stream())
                    .map(Node::getStation)
                    .forEachOrdered(pathStations::add);

            System.out.println(destination.getLines());

            currentSource = source;
            destinationSource = destination;
            pathStations.add(destination);

            isDoneSearch = true;
            notifyObservers();
        }).start();
    }

    /**
     * If the name is not null, then delete the favorite
     *
     * @param name The name of the favorite to be deleted.
     */
    public void deleteFavorite(String name) throws RepositoryException {
        if (name == null) {
            msgFavorite = INVALID_DATA;
            notifyObservers();
            return;
        }
        FavoriteDto favorite = favoriteRepository.get(name);
        if (favorite != null) {
            favoriteRepository.remove(name);
        } else {
            msgFavorite = FAVORITE_DELETE_FAIL;
        }
        resetFavorite();
        notifyObservers();
    }

    /**
     * If the source and destination are not null, and the number of favorites is less than 10, then add the favorite to
     * the repository
     *
     * @param source      The source station.
     * @param destination The destination station.
     * @param name        The name of the favorite.
     */
    public void addFavorite(StationDto source, StationDto destination, String name) throws RepositoryException {
        if (source == null || destination == null || name == null) {
            msgFavorite = INVALID_DATA;
            notifyObservers();
            return;
        }
        // Checking if the number of favorites is greater than 10. If it is, it sets the message to FAVORITE_ADD_FAIL_MAX
        // and notifies the observers.
        if (allFavorites.size() > 10) {
            msgFavorite = FAVORITE_ADD_FAIL_MAX;
            notifyObservers();
            return;
        }
        FavoriteDto newFavorite = new FavoriteDto(name, source, destination);
        System.out.println(newFavorite.getDestination().getLines());
        favoriteRepository.add(newFavorite);
        resetFavorite();
        notifyObservers();
    }

    /**
     * The function takes a name as a parameter and checks if the name is null. If it is, it sets the message to
     * INVALID_DATA and notifies the observers. If it isn't, it checks if the name is in the repository. If it isn't, it
     * sets the message to INVALID_DATA. If it is, it tries to update the favorite. If it fails, it prints the stack trace.
     * If it succeeds, it resets the favorite and notifies the observers
     *
     * @param name the name of the favorite
     * @param text
     */
    public void updateFavorite(String name, String text) {
        if (name == null) {
            msgFavorite = INVALID_DATA;
            notifyObservers();
            return;
        }

        try {
            if (favoriteRepository.get(name) == null) {
                msgFavorite = INVALID_DATA;
            }

            try {
                FavoriteDto favorite = favoriteRepository.get(name);
                FavoriteDto newFavorite = new FavoriteDto(text, favorite.getSource(), favorite.getDestination());
                favoriteRepository.remove(name);
                favoriteRepository.add(newFavorite);
                resetFavorite();
            } catch (RepositoryException e) {
                e.printStackTrace();
            }
        } catch (RepositoryException e) {
            e.printStackTrace();
        }
        notifyObservers();
    }

    /**
     * The function gets the source and destination stations from the favorite object, and then calculates the shortest
     * path between them
     *
     * @param name The name of the favorite.
     */
    public void searchByName(String name) {
        new Thread(() -> {
            try {
                makeGraph();
                FavoriteDto favorite = favoriteRepository.get(name);
                if (favorite == null || favorite.getSource() == null || favorite.getDestination() == null) {
                    isDoneSearch = false;
                    notifyObservers();
                    return;
                }
                pathStations.clear();
                // Calculating the shortest path from the source to the destination.
                Graph shortestGraph = Dijkstra.calculateShortestPathFromSource(graph, allNodeStations.get(favorite.getSource().getKey()));

                // Getting the shortest path from the source to the destination.
                shortestGraph.getNodes().stream().filter(node -> node.getStation().getKey().equals(favorite.getDestination().getKey()))
                        .flatMap(node -> node.getShortestPath().stream())
                        .map(Node::getStation)
                        .forEachOrdered(pathStations::add);

                System.out.println(favorite.getDestination().getLines());
                pathStations.add(favorite.getDestination());
                isDoneSearch = true;
                notifyObservers();
            } catch (RepositoryException e) {
                e.printStackTrace();
            }
        }).start();
    }

    /**
     * It updates the language of the application
     *
     * @param language the language that the user has selected
     */
    public void updateLanguage(LangState language) {
        System.out.println(language);
        switch (language) {
            case ND:
                try {
                    allStations.clear();
                    repository.getAllNdStations().forEach(dto -> allStations.add(dto.getStation()));
                } catch (RepositoryException e) {
                    e.printStackTrace();
                }
                break;
            default:
                try {
                    allStations.clear();
                    System.out.println("francais");
                    repository.getAll().forEach(dto -> allStations.add(dto.getStation()));
                } catch (RepositoryException e) {
                    e.printStackTrace();
                }
                break;
        }
        try {
            search(currentSource, destinationSource);
        } catch (RepositoryException e) {
            e.printStackTrace();
        }
        notifyObservers();
    }

    @Override
    public void update(Object... args) {
        notifyObservers(args);
    }

    @Override
    public void registerObserver(Observer observer) {
        if (observer == null) {
            throw new NullPointerException();
        }
        if (!this.observers.contains(observer)) {
            this.observers.add(observer);
        }
    }

    @Override
    public void removeObserver(Observer obs) {

    }

    @Override
    public void notifyObservers(Object... args) {
        for (Observer obs : observers) {
            obs.update(args);
        }
    }

    /**
     * This function returns a boolean value that indicates whether the search is done or not
     *
     * @return isDoneSearch
     */
    public boolean isDoneSearch() {
        return isDoneSearch;
    }

    /**
     * This function returns the value of the variable msgFavorite
     *
     * @return The msgFavorite variable is being returned.
     */
    public String getMsgFavorite() {
        return msgFavorite;
    }

    /**
     * This function sets the value of the variable msgFavorite to the value of the parameter msgFavorite
     *
     * @param msgFavorite The message to display when the user favorites a post.
     */
    public void setMsgFavorite(String msgFavorite) {
        this.msgFavorite = msgFavorite;
    }

    /**
     * This function returns the pathStations variable.
     *
     * @return The pathStations ObservableList is being returned.
     */
    public ObservableList<StationDto> getPathStations() {
        return pathStations;
    }

    /**
     * Return the set of all stations.
     *
     * @return ObservableSet<StationDto>
     */
    public ObservableSet<StationDto> getAllStations() {
        return allStations;
    }

    /**
     * Return an ObservableSet of FavoriteDto objects that is updated whenever the underlying data changes.
     *
     * @return A set of all the favorites.
     */
    public ObservableSet<FavoriteDto> getAllFavorites() {
        return allFavorites;
    }

}