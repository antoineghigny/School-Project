package command;

import java.util.Stack;

public class CommandManager {

    private final Stack<CommandInterface> undoStack = new Stack<>(); // Stack
    private final Stack<CommandInterface> redoStack = new Stack<>();

    public CommandManager() {

    }

    /**
     * Allows you to execute a command
     * @param commande the command to be executed
     */
    public void executeCommand(CommandInterface commande) {
        undoStack.push(commande);
        commande.execute();
        redoStack.clear();
    }

    /**
     * Allows you to cancel a command.
     */
    public void undoCommand() {
        if (!undoStack.empty()) {
            CommandInterface command = undoStack.pop();
            redoStack.push(command);
            command.undo();
        }
    }

    /**
     * Allows you to replay a command.
     */
    public void redoCommand() {
        if (!redoStack.empty()) {
            CommandInterface command = redoStack.pop();
            undoStack.push(command);
            command.execute();
        }
    }

    /**
     * Allows you to clear the stacks containing the order history.
     */
    public void clear(){
        redoStack.clear();
        undoStack.clear();
    }
}