package esi.atl.g56359.stibride.model.dao;

import esi.atl.g56359.stibride.model.dto.FavoriteDto;
import esi.atl.g56359.stibride.model.dto.StationDto;
import esi.atl.g56359.stibride.model.utils.RepositoryException;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.*;

class FavoriteDaoTest {
    private final FavoriteDto home;
    private final FavoriteDto notExist;

    private final List<FavoriteDto> all;

    private FavoriteDao instance;

    public FavoriteDaoTest() {
        notExist = new FavoriteDto("notExist", new StationDto(8292, "DE BROUCKERE"), new StationDto(8382, "GARE DE L'OUEST"));
        all = new ArrayList<>();
        all.add(new FavoriteDto("other", new StationDto(8652, "EDDY MERCKX"), new StationDto(8754, "OSSEGHEM")));
        home = new FavoriteDto("home", new StationDto(8641, "ERASME"), new StationDto(8742, "BEEKKANT"));
        all.add(home);

        try {
            instance = FavoriteDao.getInstance();
        } catch (RepositoryException ex) {
            org.junit.jupiter.api.Assertions.fail("Error connection to database", ex);
        }
    }


    @Test
    void testSelectAll() throws RepositoryException {
        List<FavoriteDto> result = instance.selectAll();
        boolean found = false;
        for (FavoriteDto item : all) {
            found = false;
            for (var itemBdd : result) {
                if (itemBdd.equals(item)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                break;
            }
        }
        assertTrue(found);
    }

    @Test
    void testSelect() throws RepositoryException {
        FavoriteDto result = instance.select("home");
        assertEquals(home, result);
    }

    @Test
    void testSelectNotExist() throws RepositoryException {
        FavoriteDto result = instance.select(notExist.getKey());
        assertNull(result);
    }

    @Test
    void testInsert() throws RepositoryException {
        var newFavorite = new FavoriteDto("added0", new StationDto(8652, "EDDY MERCKX"), new StationDto(8754, "OSSEGHEM"));
        List<FavoriteDto> resultBefore = instance.selectAll();
        instance.insert(newFavorite);
        List<FavoriteDto> resultAfter = instance.selectAll();
        assertEquals(resultBefore.size(), resultAfter.size() - 1);
        Assertions.assertEquals(newFavorite, instance.select("added0"));
        instance.delete("added0");
    }

    @Test
    void testInsertEmptyValue() {
        assertThrows(RepositoryException.class, () -> {
            instance.insert(null);
        });
    }


    @Test
    void testDelete() throws RepositoryException {
        var newFavorite = new FavoriteDto("added2", new StationDto(8652, "EDDY MERCKX"), new StationDto(8754, "OSSEGHEM"));
        instance.insert(newFavorite);
        List<FavoriteDto> resultBefore = instance.selectAll();
        instance.delete("added2");
        List<FavoriteDto> resultAfter = instance.selectAll();
        assertEquals(resultBefore.size() - 1, resultAfter.size());
        assertNull(instance.select("added2"));
    }

    @Test
    void testDeleteEmptyValue() throws RepositoryException {
        assertThrows(RepositoryException.class, () -> {
            instance.delete(null);
        });
    }

    @Test
    void testUpdate() throws RepositoryException {
        var newFavorite = new FavoriteDto("added3", new StationDto(8652, "EDDY MERCKX"), new StationDto(8754, "OSSEGHEM"));
        instance.insert(newFavorite);
        FavoriteDto resultBefore = instance.select("added3");

        var editedFavorite = new FavoriteDto("added3", new StationDto(8292, "DE BROUCKERE"), new StationDto(8382, "GARE DE L'OUEST"));
        instance.update(editedFavorite);
        FavoriteDto resultAfter = instance.select("added3");

        assertEquals(resultBefore.getDestination(), newFavorite.getDestination());
        assertEquals(resultBefore.getSource(), newFavorite.getSource());
        assertEquals(resultAfter.getDestination(), editedFavorite.getDestination());
        assertEquals(resultAfter.getSource(), editedFavorite.getSource());
        instance.delete("added3");
    }

    @Test
    void testUpdateEmptyValue() throws RepositoryException {
        assertThrows(RepositoryException.class, () -> {
            instance.update(null);
        });
    }
}