
package command;

import view.View;


public class Help implements Command{
    
    private View view;
    
    public Help(View view){
        this.view = view;
    }
    
    @Override
    public String execute() {
        return view.helpCommand();
    }
}
