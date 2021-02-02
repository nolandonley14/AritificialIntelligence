class Cell {

  constructor() {
    this.xCoord = 0;
    this.yCoord = 0;
    this.radius = 0;
    this.state = false;
    this.neighbors = [];
    this.age = 0;
  }

  dragged(px, py, page) {
    if (page == "draw") {
      let d = dist(px, py, this.xCoord, this.yCoord);
      if (d < this.radius) {
        if (!this.state) {
          this.state = true;
        }
      }
    }
  }

  clicked(px, py, page) {
    if (page == "draw") {
      let d = dist(px, py, this.xCoord, this.yCoord);
      if (d < this.radius) {
        if (!this.state) {
          this.state = true;
        } else {
          this.state = false;
        }
      }
    }
  }
}
