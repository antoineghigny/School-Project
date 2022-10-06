package command;

import model.Model;

public class Crack implements Command {
    private Model model;
    private String str;

    public Crack(Model model, String str) {
        this.model = model;
        this.str = str;
    }

    @Override
    public String execute() {
        return model.crack(str);
    }

}
