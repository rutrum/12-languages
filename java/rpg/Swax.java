import java.util.Scanner;

class Swax {

    public static void main(String[] args) {
        System.out.println("SWAX: Generic RPG");
        Monster p = new Monster("Dave");
        State state = State.WANDER;

        System.out.println(p.summary());

        Scanner input = new Scanner(System.in);

        Monster badguy = new Monster("Gremlin");

        while (p.isAlive()) {

            switch (state) {

                // Allow player to heal, look at status
                case WANDER: {
                    System.out.print("> ");
                    WanderAction action = WanderAction.parseString(input.nextLine());
                    
                    if (action == null) {
                        System.out.println("Not a valid action.");
                        continue;
                    }
                    switch (action) {
                        case FIGHT:
                            state = State.PROVOKE;
                            break;
                        case STATUS:
                            System.out.println(p.summary());
                            break;
                    }
                    break;
                }

                // Engage in a fight, spawn monster
                case PROVOKE: {
                    badguy = new Monster("Gremlin");
                    state = State.FIGHT;
                    break;
                }

                // Player and monster fight
                case FIGHT: {
                    System.out.println("Perform action [attack/heal]:");
                    FightAction action = FightAction.parseString(input.nextLine());
                    
                    if (action == null) {
                        System.out.println("noop");
                        continue;
                    }

                    switch (action) {
                        case ATTACK:
                            System.out.println("You attack for 2 points!");
                            badguy.damage(2);
                            if (badguy.isDead()) {
                                state = State.LOOT;
                                continue;
                            }
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

                    break;
                }

                // Monster dead, spawn loot
                case LOOT: {
                    System.out.println("You defeated the " + badguy.name + "!");
                    state = State.WANDER;
                    break; 
                }
            }
        }
    }
}

enum State {
    WANDER,
    PROVOKE,
    FIGHT,
    LOOT,
}

class Monster {

    class Stats {
        public int stamina; // health
        public int strength; // attack
        //public int speed; // how often one can attack
        //public int intellect; // mana
        //public int defense; // armor
        
        public Stats() {
            this.stamina = 10;
            this.strength = 3;
        }
    }

    public enum Status {
        ALIVE,
        DEAD,
    }

    public String name;
    private Status status;
    private Stats stats;
    private int level;
    private int hp;
    
    public Monster(String name) {
        this.name = name;
        this.status = Status.ALIVE;
        this.stats = new Stats();
        this.level = 1;
        this.hp = this.stats.stamina;
    }

    public String summary() {
        String s = this.name + ": level " + this.level +
            "\nHP: " + this.hp + " / " + this.stats.stamina + 
            "\nStrength: " + this.stats.strength;
        return s;
    }

    public void damage(int d) {
        if (this.hp > d) {
            this.hp -= d;
        } else {
            this.hp = 0;
            this.status = Status.DEAD;
        }
    }

    public void heal(int h) {
        this.hp += h;
        if (this.hp > this.stats.stamina) {
            this.hp = this.stats.stamina;
        }
    }

    public boolean isAlive() {
        return this.status == Status.ALIVE;
    }

    public boolean isDead() {
        return this.status == Status.DEAD;
    }
}

enum FightAction {
    ATTACK,
    HEAL,
    RUN;

    public static FightAction parseString(String s) {
        if (s.equals("attack") || s.equals("a")) {
            return ATTACK;
        } else if (s.equals("heal") || s.equals("h")) {
            return HEAL;
        } else if (s.equals("run") || s.equals("r")) {
            return HEAL;
        } else {
            return null;
        }
    }
}

enum WanderAction {
    STATUS,
    FIGHT;

    public static WanderAction parseString(String s) {
        if (s.equals("status") || s.equals("s")) {
            return STATUS;
        } else if (s.equals("fight") || s.equals("f")) {
            return FIGHT;
        } else {
            return null;
        }
    }
}
