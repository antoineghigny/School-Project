package command;

import model.Model;

public class Decypher implements Command{
    private final Model model;
    private final String str;
    private final String key;
    private final String method;

    public Decypher(Model model, String str, String key, String method) {
        this.model = model;
        this.str = str;
        this.key = key;
        this.method = method;
    }

    @Override
    public String execute() {
        return model.decypherFacade(str, key, method);
    }
}
