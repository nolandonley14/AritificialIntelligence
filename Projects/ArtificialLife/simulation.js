class Simulation {

  constructor(board, numSims, size) {
    this.gameBoard = board;
    this.gens = numSims;
    this.boardSize = size;
    this.numBirths = 0;
    this.numDeaths = 0;
    this.deathAge = [];
  }

  startSim() {
    this.getNeighbors(this.gameBoard, this.boardSize);
    this.gameBoard = this.calculateNexGeneration(this.gameBoard);
  }

  getNeighbors(b, bsize) {
    this.size = sqrt(bsize);
    for (this.i = 0; this.i < this.size; this.i++) {
      for (this.j = 0; this.j < this.size; this.j++) {
        // Top Left Square
        if (this.i== 0 && this.j == 0) {
          this.neigh = [b[0][1].state, b[1][0].state, b[1][1].state];
        }
        // Top Right Square
        else if (this.i== (this.size - 1) && this.j == 0) {
          this.neigh = [b[this.size-2][0].state, b[this.size-1][1].state, b[this.size-2][1].state];
        }
        // Bottom Right Square
        else if (this.i== (this.size - 1) && this.j == (this.size - 1)) {
          this.neigh = [b[this.size - 1][this.size - 2].state, b[this.size - 2][this.size - 1].state, b[this.size - 2][this.size - 2].state];
        }
        // Bottom Left Square
        else if (this.i== 0 && this.j == (this.size-1)) {
          this.neigh = [b[0][this.size-1].state, b[1][this.size-1].state, b[1][this.size-2].state];
        }
        // Top Row
        else if (this.i >= 1 && this.i <= (this.size - 2) && this.j == 0) {
          this.neigh = [b[this.i+1][this.j].state, b[this.i-1][this.j].state, b[this.i+1][this.j+1].state, b[this.i][this.j+1].state, b[this.i-1][this.j+1].state];
        }
        // Bottom Row
        else if (this.i>= 1 && this.i<= (this.size-2) && this.j == this.size-1) {
          this.neigh = [b[this.i+1][this.j].state, b[this.i-1][this.j].state, b[this.i-1][this.j-1].state, b[this.i][this.j-1].state, b[this.i+1][this.j-1].state];
        }
        // Left Column
        else if (this.i == 0 && this.j >= 1 && this.j < this.size-1) {
          this.neigh = [b[this.i][this.j+1].state, b[this.i][this.j-1].state, b[this.i+1][this.j-1].state, b[this.i+1][this.j].state, b[this.i+1][this.j+1].state];
        }
        // Right Column
        else if (this.i== this.size - 1 && this.j >= 1 && this.j < this.size-1) {
          this.neigh = [b[this.i][this.j+1].state, b[this.i][this.j-1].state, b[this.i-1][this.j-1].state, b[this.i-1][this.j].state, b[this.i-1][this.j+1].state];
        }
        // Everything in the middle
        else {
          this.neigh = [b[this.i-1][this.j-1].state, b[this.i][this.j-1].state, b[this.i+1][this.j-1].state, b[this.i-1][this.j].state, b[this.i+1][this.j].state, b[this.i-1][this.j+1].state, b[this.i][this.j+1].state, b[this.i+1][this.j+1].state];
        }
          b[this.i][this.j].neighbors = this.neigh;
      }
    }
  }

  calculateNexGeneration(b) {
    this.boardCopy = b;
    for (this.i=0; this.i<b.length; this.i++) {
      for(this.j = 0; this.j<b.length; this.j++) {
        this.liveNeighbors = 0;
        for (this.k=0; this.k < b[this.i][this.j].neighbors.length; this.k++) {
          if (b[this.i][this.j].neighbors[this.k] == true) {
            this.liveNeighbors++;
          }
        }
        if (this.liveNeighbors == 0 || this.liveNeighbors == 1 || this.liveNeighbors >= 4) {
            this.boardCopy[this.i][this.j].state = false;
            this.deathAge.push(this.boardCopy[this.i][this.j].age);
            this.numDeaths++;
            this.boardCopy[this.i][this.j].age = 0;
        } else if (this.liveNeighbors == 2) {
            this.boardCopy[this.i][this.j] = b[this.i][this.j];
        } else if (this.liveNeighbors == 3) {
            if (!this.boardCopy[this.i][this.j].state) {
              this.boardCopy[this.i][this.j].state = true;
              this.boardCopy[this.i][this.j].age = 0;
              this.numBirths++;
            }
        }
        if (b[this.i][this.j].age == 9) {
          this.deathAge.push(10);
          this.boardCopy[this.i][this.j].state = false;
          this.boardCopy[this.i][this.j].age = 0;
          this.numDeaths++;
        } else {
          this.boardCopy[this.i][this.j].age += 1;
        }
      }
    }
    return this.boardCopy;
  }

}
