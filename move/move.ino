/*  
  *  Использование датчика движения типа PIR с платой Arduino.
  *  Более подробно о проекте на:  randomnerdtutorials.com/pirsensor
  *  Модифицирован Руи Сантосом (Rui Santos)
     на основе скетча Лимор Фрид (Limor Fried)
*/
 
int led = 0;                 // контакт для светодиода
int sensor = 4;              // контакт для датчика
int state = LOW;             // по умолчанию никакого движения 
                             // не определено
int val = 0;                 // переменная для хранения 
                             // статуса датчика

void setup() 
{
  pinMode(led, OUTPUT);      // контакт для светодиода 
                             // ставим в режим OUTPUT 
  pinMode(sensor, INPUT);    // контакт для датчика 
                             // ставим в режим INPUT 
  Serial.begin(9600);        // инициализируем последовательную 
                             // коммуникацию
  digitalWrite(led, LOW);
}


void loop()
{
  val = digitalRead(sensor);   // считываем данные от датчика
  if ( val == HIGH ){           // проверяем, находится ли датчик
                               // в состоянии HIGH 
    digitalWrite(led, HIGH);   // включаем светодиод
    delay(100);                // задержка в 100 миллисекунд
    
    if ( state == LOW ){
      Serial.println("Motion detected!");  //  "Замечено движение!"
      state = HIGH;       // обновляем состояние переменной на HIGH 
    }
    digitalWrite(led, LOW);   // включаем светодиод
    delay(500);                // задержка в 100 миллисекунд
  } else {
      digitalWrite(led, LOW); // выключаем светодиод
      delay(100);             // задержка в 200 миллисекунд 
      
      if ( state == HIGH ){
        Serial.println("Motion stopped!"); //  "Движение прекращено!"
        state = LOW;       // обновляем состояние переменной на LOW
    }
  }
}
