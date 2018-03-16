
package whackamole;

import java.util.Random;
import java.util.Scanner;


public class WhackAMole {

    private int score, molesLeft, attemptsLeft;
    private final int gridDimension;
    private final Character[][] moleGrid; 
    
    
    WhackAMole(int numAttempts, int gridDimension) {
        score = 0;
        molesLeft = 0;
        
        this.gridDimension = gridDimension;
        attemptsLeft = numAttempts;
        moleGrid = new Character[gridDimension][gridDimension]; 
        initializeGrid();
    }
    
    int getAttempts() {
        return attemptsLeft;
    }
    
    int getMolesLeft() {
        return molesLeft;
    }
    
    // Fill grid with *
    private void initializeGrid() {
        for (int i = 0; i < gridDimension; i++) {
            for (int j = 0; j < gridDimension; j++) {
                moleGrid[i][j] = '*';
            }
        }
    }
    
    // Placing a mole on the grid, upadting molesLeft
    boolean place(int x, int y) {
        if (x >= gridDimension || y >= gridDimension) {
            System.out.println("Cannot place mole in place x:" + x + ", y:" + y 
                    + " because grid is " + gridDimension + " by " + gridDimension + " square.");
            return false;
        } else if (moleGrid[x][y] == 'M' || moleGrid[x][y] == 'W') {
            System.out.println("Cannot place mole in place because this place is occupied");
            return false;
        } else {
        moleGrid[x][y] = 'M';
        molesLeft++;
        return true;
        }
    }
    
    // Updating score, attempts, trying to whack a mole
    void whack(int x, int y) {
        if (x >= gridDimension || y >= gridDimension) {
            System.out.println("Cannot whack in place x:" + x + ", y:" + y 
                    + " because grid is " + gridDimension + " by " + gridDimension + " square.");
        } else if (moleGrid[x][y] == 'W') {
            System.out.println("You already whacked there!");
        } else if (moleGrid[x][y] == 'M') {
            System.out.println("You whacked a mole!");
            attemptsLeft--;
            molesLeft--;
            score++;
            moleGrid[x][y] = 'W';
        } else attemptsLeft--;
    }
    
    // Printing grid with moles hidden
    void printGridToUser() {
        for (int i = 0; i < gridDimension; i++) {
            for (int j = 0; j < gridDimension; j++) {
                if (moleGrid[i][j] == 'M') System.out.print('*');
                else System.out.print(moleGrid[i][j]);
            }
            System.out.println();
        }
    }
    
    // Printing grid with moles shown
    void printGrid() {
        System.out.println("--------------");
        for (int i = 0; i < gridDimension; i++) {
            for (int j = 0; j < gridDimension; j++) {
                System.out.print(moleGrid[i][j]);
            }
            System.out.println();
        }
    }
    
    // Finish the game
    void gameEnd() {
        printGrid();
        System.out.println("Score is   = " + score);
        System.out.println("Moles left = " + molesLeft);
    }
    
    public static void main(String[] args) {
        Random rand = new Random();
        WhackAMole game = new WhackAMole(20, 5);
        System.out.println("Created game.");
        
        // Filling grid with moles
        for (int i = 0; i < 10; i++) {
            boolean success;
            do {
            System.out.println(i + ". Trying to place a mole");
            success = game.place(rand.nextInt(5), rand.nextInt(5));
            } while (!success);
        }
        
        Scanner in = new Scanner(System.in);
        while (game.attemptsLeft > 0 && game.getMolesLeft() > 0) {
            System.out.println("Attempts left: " + game.getAttempts());
            System.out.println("Where to whack? x, y?");
            int x = in.nextInt();
            int y = in.nextInt();
            game.whack(x, y);
            game.printGridToUser();
        }
        game.gameEnd();
    }
    
}
