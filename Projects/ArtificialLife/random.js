var bgcolor;
var canvas;
var button;
var colonySize;
var numGenerations;
var sizeNum;
var genNum;
var generationNumber;
var initialLifeRate;
var animationRate;
var lifeRate;
var aniRate;
var sim;
var int;
var sizeNumFull;
var iterator = 0;
var average;
var endLife;
var tempGenNum = 0;
var gameCells = [];
var dropzone;
var tab = "random";

function setup() {
  //Universal Properties
  bgcolor = color("lightblue");
  canvas = createCanvas(500, 500);
  canvas.parent('canvasContainer');

  //Navigation buttons
  randTab = select('#Random');
  randTab.mousePressed(canvasToRandom);
  dndTab = select('#DragDrop');
  dndTab.mousePressed(canvasToDragDrop);
  drawTab = select('#Draw');
  drawTab.mousePressed(canvasToDraw);

  // Random Tab Properites
  colonySize = select('#colonySize');
  numGenerations = select('#numGen');
  initialLifeRate = select('#life');
  animationRate = select('#animate');
  sizeNumFull = colonySize.value();
  sizeNum = select('#colSize');
  genNum = select('#genNum');
  lifeRate = select('#lRate');
  aniRate = select('#frameRate');
  sizeNum.html(pow(colonySize.value(),2));
  genNum.html(numGenerations.value());
  lifeRate.html(initialLifeRate.value() * 5 + "%");
  aniRate.html(animationRate.value() + ' ms');
  colonySize.input(updateSizeNum);
  numGenerations.input(updateGenNum);
  initialLifeRate.input(updateLifeRate);
  animationRate.input(updateAnimationRate);
  generationNumber = select('#currentGen');
  button = select('#simButton');
  button.mousePressed(SimulatePopulation);
  startingLife = select('#startAlive');
  endingLife = select('#endAlive');
  birthToll = select('#numBirths');
  deathToll = select('#numDeaths');
  AvgLifeSpan = select('#avgLife');
  setPopulationUp();

  // Drag and Drop Tab Properties
  dropzone = select('#dropzone');
  dropzone.dragOver(highlight);
  dropzone.dragLeave(unhighlight);
  dropzone.drop(handleFile, unhighlight);
  button2 = select('#simButton2');
  button2.mousePressed(SimulatePopulation2);
  numGenerations2 = select('#numGen2');
  animationRate2 = select('#animate2');
  genNum2 = select('#genNum2');
  aniRate2 = select('#frameRate2');
  genNum2.html(numGenerations2.value());
  aniRate2.html(animationRate2.value() + ' ms');
  numGenerations2.input(updateGenNum);
  animationRate2.input(updateAnimationRate);
  generationNumber2 = select('#currentGen2');
  startingLife2 = select('#startAlive2');
  endingLife2 = select('#endAlive2');
  birthToll2 = select('#numBirths2');
  deathToll2 = select('#numDeaths2');
  AvgLifeSpan2 = select('#avgLife2');

  // Draw Properties
  button3 = select('#simButton3');
  button3.mousePressed(SimulatePopulation3);
  colonySize3 = select('#colonySize3');
  numGenerations3 = select('#numGen3');
  animationRate3 = select('#animate3');
  sizeNum3 = select('#colSize3');
  genNum3 = select('#genNum3');
  aniRate3 = select('#frameRate3');
  sizeNum3.html(pow(colonySize3.value(),2));
  genNum3.html(numGenerations3.value());
  aniRate3.html(animationRate3.value() + ' ms');
  colonySize3.input(updateSizeNum3);
  numGenerations3.input(updateGenNum);
  animationRate3.input(updateAnimationRate);
  generationNumber3 = select('#currentGen3');
  startingLife3 = select('#startAlive3');
  endingLife3 = select('#endAlive3');
  birthToll3 = select('#numBirths3');
  deathToll3 = select('#numDeaths3');
  AvgLifeSpan3 = select('#avgLife3');
}

function getStartingNum() {
  startingNum = 0;
  for (var i = 0; i < sizeNumFull; i++) {
    for (var j = 0; j < sizeNumFull; j++) {
      if (gameCells[i][j].state)
      startingNum++;
    }
  }
  startingLife3.html(startingNum);
  endingLife3.html(startingNum);
}


function mouseDragged() {
  for (var i = 0; i < sizeNumFull; i++) {
    for (var j = 0; j < sizeNumFull; j++) {
      gameCells[i][j].dragged(mouseX, mouseY,tab);
      getStartingNum();
    }
  }
}

function mouseClicked() {
  for (var i = 0; i < sizeNumFull; i++) {
    for (var j = 0; j < sizeNumFull; j++) {
      gameCells[i][j].clicked(mouseX, mouseY, tab);
      getStartingNum();
    }
  }
}

function handleFile(file) {
  console.log(file);
  if (file.subtype == "plain" && file.type == "text") {
    var text = file.data;
    var trim = text.trim();
    var splitStr = trim.replace(/[\r\n]+/gm, "");
    var arr = splitStr.split(' ');
    resetLabels();
    gameCells = [];
    var startingNum = 0;
    sizeNumFull = sqrt(arr.length);
    for (var i = 0; i < sizeNumFull; i++) {
      gameCells[i] = [];
      for (var j = 0; j < sizeNumFull; j++) {
        cell = new Cell();
        if (arr[i*sizeNumFull+j] == 'X') {
          cell.state = true;
          startingNum++;
        } else {
          cell.state = false;
        }
        gameCells[i][j] = cell;
      }
    }
    temp = [];
    for (var i = 0; i < gameCells[0].length; i++) {
      temp[i] = [];
      for (var j = 0; j < gameCells.length; j++) {
        temp[i][j] = gameCells[j][i];
      }
    }
    gameCells = temp;
    startingLife2.html(startingNum);
    endingLife2.html(startingNum);
    sim = new Simulation(gameCells, numGenerations.value(), pow(gameCells.length, 2));
  }
}

function highlight() {
  dropzone.style('background-color', "skyblue");
}

function unhighlight() {
  dropzone.style('background-color', "lightblue");
}

function canvasToRandom() {
  tab = "random";
  canvas.parent('canvasContainer');
}

function canvasToDragDrop() {
  tab = "dragdrop";
  emptyColony();
  canvas.parent('canvasContainer2');
}

function canvasToDraw() {
  tab = 'draw';
  emptyColony();
  canvas.parent('canvasContainer3');
}

function emptyColony() {
  for (var i = 0; i < sizeNumFull; i++) {
    for (var j = 0; j < sizeNumFull; j++) {
        gameCells[i][j].state = false;
    }
  }
}

function setPopulationUp() {
  resetLabels();
  gameCells = [];
  var startingNum = 0;
  for (var i = 0; i < sizeNumFull; i++) {
    gameCells[i] = [];
    for (var j = 0; j < sizeNumFull; j++) {
      cell = new Cell();
      ran = floor(random() * 11);
      if (ran >= initialLifeRate.value()/2) {
        cell.state = false;
      } else {
        cell.state = true;
        startingNum++;
      }
      gameCells[i][j] = cell;
    }
  }
  startingLife.html(startingNum);
  endingLife.html(startingNum);
  sim = new Simulation(gameCells, numGenerations.value(), pow(gameCells.length, 2));
}

function blankSetUp() {
  resetLabels();
  generationNumber3.html(0);
  gameCells = [];
  var startingNum = 0;
  for (var i = 0; i < sizeNumFull; i++) {
    gameCells[i] = [];
    for (var j = 0; j < sizeNumFull; j++) {
      cell = new Cell();
      gameCells[i][j] = cell;
    }
  }
  startingLife.html(startingNum);
  endingLife.html(startingNum);
  sim = new Simulation(gameCells, numGenerations.value(), pow(gameCells.length, 2));
}

function resetLabels() {
  tempGenNum = 0;
  birthToll.html('0');
  deathToll.html('0');
  generationNumber.html(iterator);
  AvgLifeSpan.html('0');
}

function checkBoard() {
  endLife = 0;
  for (var i = 0; i < sizeNumFull; i++) {
    for (var j = 0; j < sizeNumFull; j++) {
        if (sim.gameBoard[i][j].state) {
          endLife++;
        }
    }
  }
  return endLife;
}

function updateSizeNum() {
  if (int) {
    clearInterval(int);
  }
  sizeNum.html(pow(colonySize.value(),2));
  sizeNumFull = colonySize.value();
  setPopulationUp();
}

function updateSizeNum3() {
  if (int) {
    clearInterval(int);
  }
  sizeNum3.html(pow(colonySize3.value(),2));
  sizeNumFull = colonySize3.value();
  blankSetUp();
}

function updateLifeRate() {
      lifeRate.html(initialLifeRate.value() * 5 + "%");
      setPopulationUp();
}

function updateAnimationRate() {
      aniRate.html(animationRate.value() + ' ms');
      aniRate2.html(animationRate2.value() + ' ms');
      aniRate3.html(animationRate3.value() + ' ms');
}

function updateGenNum() {
      genNum.html(numGenerations.value());
      genNum2.html(numGenerations2.value());
      genNum3.html(numGenerations3.value());
}

function SimulatePopulation() {
  int = setInterval(simulate, animationRate.value())
  var sum = 0;
  function simulate() {
    iterator+=1;
    tempGenNum += 1;
    generationNumber.html(tempGenNum);
    sim.startSim();
    redraw();
    if (iterator == numGenerations.value()) {
      clearInterval(int);
      birthToll.html(sim.numBirths);
      deathToll.html(sim.numDeaths);
      endingLife.html(checkBoard());
      for (var i = 0; i < sim.deathAge.length; i++) {
        sum += sim.deathAge[i];
      }
      average = sum/sim.deathAge.length;
      AvgLifeSpan.html(average.toPrecision(4));
      iterator = 0;
    }
  }
}

function SimulatePopulation2() {
  int = setInterval(simulate2, animationRate2.value())
  var sum = 0;
  function simulate2() {
    iterator+=1;
    tempGenNum += 1;
    generationNumber2.html(tempGenNum);
    sim.startSim();
    redraw();
    if (iterator == numGenerations2.value()) {
      clearInterval(int);
      birthToll2.html(sim.numBirths);
      deathToll2.html(sim.numDeaths);
      endingLife2.html(checkBoard());
      for (var i = 0; i < sim.deathAge.length; i++) {
        sum += sim.deathAge[i];
      }
      average = sum/sim.deathAge.length;
      AvgLifeSpan2.html(average.toPrecision(4));
      iterator = 0;
    }
  }
}

function SimulatePopulation3() {
  int = setInterval(simulate3, animationRate3.value())
  var sum = 0;
  function simulate3() {
    iterator+=1;
    tempGenNum += 1;
    generationNumber3.html(tempGenNum);
    sim.startSim();
    redraw();
    if (iterator == numGenerations3.value()) {
      clearInterval(int);
      birthToll3.html(sim.numBirths);
      deathToll3.html(sim.numDeaths);
      endingLife3.html(checkBoard());
      for (var i = 0; i < sim.deathAge.length; i++) {
        sum += sim.deathAge[i];
      }
      average = sum/sim.deathAge.length;
      AvgLifeSpan3.html(average.toPrecision(4));
      iterator = 0;
    }
  }
}

function draw() {
  background(bgcolor);
  for (var i = 0; i <sizeNumFull; i++) {
    for (var j = 0; j <sizeNumFull; j++) {
      var x = i * 500/sizeNumFull + 500/sizeNumFull/2;
      var y = j * 500/sizeNumFull + 500/sizeNumFull/2;
      sim.gameBoard[i][j].xCoord = x;
      sim.gameBoard[i][j].yCoord = y;
      sim.gameBoard[i][j].radius = 500/sizeNumFull/2;
        if (sim.gameBoard[i][j].state == false) {
          fill(255);
        } else {
          switch (sim.gameBoard[i][j].age) {
            case 0:
              fill(57, 255, 20);
              break;
            case 1:
              fill(93, 255, 50);
              break;
            case 2:
              fill(159, 255, 0);
              break;
            case 3:
              fill(192, 255, 98);
              break;
            case 4:
              fill(251, 255, 112);
              break;
            case 5:
              fill(251, 214, 93);
              break;
            case 6:
              fill(226, 162, 66);
              break;
            case 7:
              fill(255, 143, 53);
              break;
            case 8:
              fill(255, 96, 51);
              break;
            case 9:
              fill(255, 27, 14);
              break;
          }
        }
        strokeWeight(0.5);
        stroke(80);
        ellipse(x, y, 500/sizeNumFull, 500/sizeNumFull);
    }
  }

}
