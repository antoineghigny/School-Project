package esi.atl.g56359.stibride.model.dao;

import esi.atl.g56359.stibride.model.dto.FavoriteDto;
import esi.atl.g56359.stibride.model.dto.StationDto;
import esi.atl.g56359.stibride.model.utils.ConfigManager;
import esi.atl.g56359.stibride.model.utils.RepositoryException;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class FavoriteDao implements Dao<String, FavoriteDto> {
    private final Connection connexion;

    public FavoriteDao() throws RepositoryException {
        connexion = ConfigManager.getInstance().getConnection();
    }

    /**
     * > The function returns an instance of the FavoriteDao class
     *
     * @return A singleton instance of the FavoriteDao class.
     */
    public static FavoriteDao getInstance() throws RepositoryException {
        return FavoriteDao.FavoriteDaoHolder.getInstance();
    }

    /**
     * It selects all the favorites from the database and returns them as a list of FavoriteDto objects
     *
     * @return A list of FavoriteDto objects.
     */
    @Override
    public List<FavoriteDto> selectAll() throws RepositoryException {
        String sql = "SELECT src.name src_name, dest.name dest_name, id_source, " + "id_destination, favorite_name " + "FROM favorites JOIN stations src ON id_source = src.id JOIN " + "stations dest ON id_destination = dest.id";
        List<FavoriteDto> favorites = new ArrayList<>();
        try (Statement stmt = connexion.createStatement()) {
            ResultSet rs = stmt.executeQuery(sql);

            while (rs.next()) {
                FavoriteDto dto = new FavoriteDto(rs.getString("favorite_name"), new StationDto(rs.getInt("id_source"), rs.getString("src_name")), new StationDto(rs.getInt("id_destination"), rs.getString("dest_name")));
                favorites.add(dto);
            }
        } catch (SQLException e) {
            throw new RepositoryException(e);
        }
        return favorites;
    }

    /**
     * It selects a favorite from the database
     *
     * @param key the name of the favorite
     * @return A FavoriteDto object
     */
    @Override
    public FavoriteDto select(String key) throws RepositoryException {
        if (key == null) {
            throw new RepositoryException("Erreur avec les objets donnés");
        }
        String sql = "SELECT src.name src_name, dest.name dest_name, id_source, " + "id_destination, favorite_name FROM " + "favorites JOIN stations src ON id_source = src.id JOIN stations " + "dest ON id_destination = dest.id WHERE favorite_name = ?";
        FavoriteDto favorite = null;
        try (PreparedStatement pstmt = connexion.prepareStatement(sql)) {
            pstmt.setString(1, key);
            ResultSet rs = pstmt.executeQuery();
            int count = 0;
            while (rs.next()) {
                favorite = new FavoriteDto(rs.getString("favorite_name"), new StationDto(rs.getInt("id_source"), rs.getString("src_name")), new StationDto(rs.getInt("id_destination"), rs.getString("dest_name")));
                count++;
            }
            if (count > 1) {
                throw new RepositoryException("Record pas unique " + key);
            }
        } catch (SQLException e) {
            throw new RepositoryException(e);
        }
        return favorite;
    }

    /**
     * It inserts a new favorite in the database
     *
     * @param item the FavoriteDto object to insert
     * @return The key of the item.
     */
    @Override
    public String insert(FavoriteDto item) throws RepositoryException {
        if (item == null) {
            throw new RepositoryException("Aucune élément donné en paramètre");
        }
        Integer id = 0;
        String sql = "INSERT INTO favorites(id_source, id_destination, favorite_name) " + "values(?, ?, ?)";
        try (PreparedStatement pstmt = connexion.prepareStatement(sql)) {
            pstmt.setInt(1, item.getSource().getKey());
            pstmt.setInt(2, item.getDestination().getKey());
            pstmt.setString(3, item.getKey());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException(e);
        }
        return item.getKey();
    }

    /**
     * It deletes a favorite from the database
     *
     * @param key the name of the favorite to delete
     */
    @Override
    public void delete(String key) throws RepositoryException {
        if (key == null) {
            throw new RepositoryException("Aucune clé donnée en paramètre");
        }
        String sql = "DELETE FROM favorites WHERE favorite_name = ?";
        try (PreparedStatement pstmt = connexion.prepareStatement(sql)) {
            pstmt.setString(1, key);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException(e);
        }
    }

    /**
     * It updates a favorite in the database
     *
     * @param item the FavoriteDto object to update
     */
    @Override
    public void update(FavoriteDto item) throws RepositoryException {
        if (item == null) {
            throw new RepositoryException("Aucune élément donné en paramètre");
        }
        String sql = "UPDATE favorites SET favorite_name = ? where id_source = ? AND where id_destination = ?";
        try (PreparedStatement pstmt = connexion.prepareStatement(sql)) {
            pstmt.setString(1, item.getKey());
            pstmt.setInt(2, item.getSource().getKey());
            pstmt.setInt(3, item.getDestination().getKey());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            throw new RepositoryException(e.getMessage());
        }
    }

    /**
     * The FavoriteDaoHolder class is a static class that has a static method called getInstance() that returns a new
     * FavoriteDao object
     */
    private static class FavoriteDaoHolder {

        private static FavoriteDao getInstance() throws RepositoryException {
            return new FavoriteDao();
        }
    }

}
