let Information = []; 

main();

async function main(){
  Information = await getData(); 
  const InformationO = document.querySelector("#IDTable");
  const printForEmailUser= document.querySelector("#EMAIL");
  const printForBirthUser= document.querySelector("#Birth");
  const NameWithA=document.querySelector("#Name");
  const uniBirthday=document.querySelector('#uni');
  const Numberphone=document.querySelector("#NUM");  

// Q1: 
  for(const data of Information)
  {
    InformationO.innerHTML +=
    `<tr>
      <td>${data.id}</td>
      <td>${data.name}</td>
      <td>${data.birthday}</td>
      <td>${data.age}</td>
      <td>${data.email}</td>
      <td>${data.mobile}</td>
    </tr>`;   
  }

  // Q2:
    const gmailUsers = Information.filter(user => user.email.endsWith("@gmail.com")) .map(user => `${user.name} - ${user.email}`);
    console.log(gmailUsers);
    printForEmailUser.innerHTML=gmailUsers.join(`<br/>`);

  // Q3:
  Cavg(); 

  //Q4
  const dayUser=Information.filter(user => user.birthday.endsWith("Mon")) .map(user => `${user.name} - ${user.birthday}`);
  printForBirthUser.innerHTML=dayUser.join(`<br/>`);
  console.log(dayUser);
//Q5
  const NameA=Information.filter(user=>user.name.startsWith("A")).map(user=>`${user.name}`);
  NameWithA.innerHTML=NameA.join(`<br/>`);
  console.log(NameA);

  //Q6
  const UniBirthday=Information.map(user=>`${user.birthday}`);
  const countMap=new Map();
  UniBirthday.forEach(day=>{countMap.set(day,(countMap.get(day)||0)+1);
  });
  
  for(let[day,count] of countMap.entries())
  {
    if(count===1)
      uniBirthday.innerHTML=`${day}<br/>`;
      console.log(day)
  }

  //Q7
  const NumberPh=Information.filter(user=>user.mobile.includes("0")).map(user=>`${user.name} - ${user.mobile}`);
  Numberphone.innerHTML=NumberPh.join(`<br/>`);
  console.log(NumberPh);

  //Q8
  ScoreAvg();

  //Q9
  get3Top();

  //Q10 
  getWinner();

  //Q11
  getRpass();

  //Q12
  getOdd();
  }


function Cavg() {
  const Av = document.querySelector("#AVG"); 
  let total = 0;
  let count = 0;

  for (let i = 0; i < Information.length; i++) {
    if (Information[i].age >= 25) {
      total += Number(Information[i].age);
      count++;      
    }
  }
  let avg =(total / count)  ;
  Av.innerHTML = `the AVG of all ages that older than 25 = ${avg}`;//.toFixed(2)
}

function ScoreAvg()
{
  const ScoreAvg=document.querySelector("#scoreAVG");

  let total=0;
  let count=0;
  for(let i=0;i<Information.length;i++)
  {
    if(Information[i].score>60)
    {
      total+=Number(Information[i].score);
      count++;
    }
  }
  let avg=total/count;
  ScoreAvg.innerHTML=` the average of all scores that greater than 60 = ${avg}`;
}

function get3Top()
{
  const HeightAvg=document.querySelector("#IDforHeightAvg");
  const sorted = [...Information].sort((a, b) => Number(b.score) - Number(a.score));
  const top3 = sorted.slice(0, 3);

  for(const HV of top3)
    {
          HeightAvg.innerHTML +=
          `<tr>
            <td>${HV.id}</td>
            <td>${HV.name}</td>
            <td>${HV.birthday}</td>
            <td>${HV.age}</td>
            <td>${HV.email}</td>
            <td>${HV.mobile}</td>
          </tr>`;   
        }
}

function getWinner()
{
  const theWineerID=document.querySelector("#IDforWinners");
  
  for(let i=0;i<Information.length;i++)
  {
    if(Information[i].age>=30)
    {
        theWineerID.innerHTML+=
          `<tr>
            <td>${Information[i].id}</td>
            <td>${Information[i].name}</td>
            <td>${Information[i].birthday}</td>
            <td>${Information[i].age}</td>
            <td>${Information[i].email}</td>
            <td>${Information[i].mobile}</td>
          </tr>`;  
    }
  }
}

function getRpass() {
  const IDpass = document.querySelector("#IDforPass");

  const result = Information.map(user => {
    const PassName = user.name.slice(0, 3).toLowerCase();
    const PassBirth = user.birthday; 
    const PassNum = user.mobile.slice(-4);
    const Thepass = (PassName + PassBirth + PassNum).split("");
    const FinalPass = Thepass.sort(() => 0.5 - Math.random()).join("");
    
    return `<p>${user.name} - The Suggested Password: <strong>${FinalPass}</strong></p>`;
  });

  IDpass.innerHTML = result.join("");
}

function getOdd() {
  const IDodd = document.querySelector("#IDforOdd");
  const resultList = [];

  for (let i = 0; i < Information.length; i++) {
    const person = Information[i];
    const firstChar = person.id.toString().charAt(0);
    const firstDigit = parseInt(firstChar);
    const isOdd = firstDigit % 2 !== 0;
    resultList.push({name: person.name,winner: isOdd});
  }

  for(const item of resultList)
  {
    IDodd.innerHTML+=
      `<tr>
      <td>${item.name}</td>
      <td>${item.winner}</td>
    </tr>`;  
    
  }
}


async function getData(){
  const res = await fetch("data.json");
  const data = await res.json();
  return data;
}
