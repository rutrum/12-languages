import java.util.Scanner;

class Swax {

    public static void main(String[] args) {
        System.out.println("SWAX: Generic RPG");
        Monster p = new Monster("Dave");
        System.out.println(p.summary());

        Scanner input = new Scanner(System.in);

        Monster badguy = new Monster("Gremlin");

        while (p.isAlive()) {
            System.out.println("Perform action [attack/heal]:");
            Action action = Action.parseString(input.nextLine());
            
            if (action == null) {
                System.out.println("noop");
                continue;
            }

            switch (action) {
                case ATTACK:
                    System.out.println("You attack for 2 points!");
                    badguy.damage(2);
                    break;
                case HEAL:
                    System.out.println("You healed 3 points!");
                    p.heal(3);
                    break;
            }

            // Monster's turn
            if (badguy.isAlive()) {
                System.out.println(badguy.summary());
                System.out.println(badguy.name + " deals 2 damage to you!");
                p.damage(2);
            }
        }
    }
}

class Monster {

    public enum Status {
        ALIVE,
        DEAD,
    }

    public String name;
    private Status status;
    private int level;
    private int maxHP;
    private int curHP;
    
    public Monster(String name) {
        this.name = name;
        this.status = Status.ALIVE;
        this.level = 1;
        this.maxHP = this.curHP = 10;
    }

    public String summary() {
        String s = this.name + ": level " + this.level +
            "\nHP: " + this.curHP + " / " + this.maxHP;
        return s;
    }

    public void damage(int d) {
        if (this.curHP > d) {
            this.curHP -= d;
        } else {
            this.curHP = 0;
            this.status = Status.DEAD;
        }
    }

    public void heal(int h) {
        this.curHP += h;
        if (this.curHP > this.maxHP) {
            this.curHP = this.maxHP;
        }
    }

    public boolean isAlive() {
        return this.status == Status.ALIVE;
    }

    public boolean isDead() {
        return this.status == Status.DEAD;
    }
}

enum Action {
    ATTACK,
    HEAL;

    public static Action parseString(String s) {
        if (s.equals("attack")) {
            return ATTACK;
        } else if (s.equals("heal")) {
            return HEAL;
        } else {
            return null;
        }
    }
}
