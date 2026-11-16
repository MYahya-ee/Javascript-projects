let Wins = 0;
let losses = 0;
let ties = 0;
function randomSign(){
    const randomNumber = Math.random();
    if (randomNumber < 1/3){
        return 'Rock';
    }
    else if(randomNumber < 2/3){
        return 'Paper';
    }
    else {
        return 'Scissor';
    }
}

function gameEngine(yourPick, enemyPick){
    if (yourPick===enemyPick){
        ties ++;
        return 'Draw';
    }

    const playerWins = (yourPick==='Rock' && enemyPick==='Scissor')||(yourPick==='Scissor' && enemyPick==='Paper')||(yourPick==='Paper' && enemyPick==='Rock')

    if (playerWins){
        Wins++;
        return 'You Won!';
    }
    else{
        losses++;
        return 'You Lose';
    }
}

function playGame(yourPick){
    const enemyPick = randomSign();
    const result = gameEngine(yourPick,enemyPick);

    console.log(`You picked: ${yourPick}`);
    console.log(`Enemy picked: ${enemyPick}`);
    console.log(`Results: ${result}`)

}