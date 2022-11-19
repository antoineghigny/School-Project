package esi.atl.g56359.stibride.model.utils;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Objects;
import java.util.Properties;

public class ConfigManager {

    private static final String FILE = "./config/config.properties";

    private final Properties prop;

    private final String url;

    private Connection connection;

    private ConfigManager() {
        prop = new Properties();
        url = Objects.requireNonNull(getClass().getClassLoader().getResource(FILE)).getFile();
    }

    public static ConfigManager getInstance() {
        return DBManagerHolder.INSTANCE;
    }

    public void load() throws IOException {
        try (InputStream input = new FileInputStream(url)) {
            prop.load(input);
        } catch (IOException ex) {
            throw new IOException("Chargement configuration impossible ", ex);
        }
    }

    /**
     * It loads the config file, gets the database url from the config file, and then connects to the database
     *
     * @return A connection to the database.
     */
    public Connection getConnection() {
        try {
            ConfigManager.getInstance().load();
            String dbUrl = prop.getProperty("db.url");
            connection = DriverManager.getConnection("jdbc:sqlite:" + dbUrl);
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
        return connection;
    }


    private static class DBManagerHolder {
        private static final ConfigManager INSTANCE = new ConfigManager();
    }
}
