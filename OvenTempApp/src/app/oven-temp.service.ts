import { Injectable } from '@angular/core';
import { Observable, Subject } from "rxjs";
import { WebsocketService } from "./websocket.service";
import { map } from 'rxjs/operators';



const ovenTempUrl: string = "wss://wsoventemp.magix.net.br";

export interface Message {
  tempCelsius: string;
  tempFarenheit: string;
  date: Date;
}

@Injectable({
  providedIn: 'root'
})
export class OvenTempService {

  public msg: Subject<Message>;

  constructor(wsService: WebsocketService) {
    this.msg = <Subject<Message>>wsService.connect(ovenTempUrl).pipe(map(
      (response: MessageEvent): Message => {
        let data = response.data;
        console.log(data);
        let aux = data.split("|");

        let tempCelsius = "0.0";
        let tempFarenheit = "0.0";

        if (aux.length > 1) {
          tempCelsius = aux[0];
          tempFarenheit = aux[1];
        }

        return {
          tempCelsius: tempCelsius,
          tempFarenheit: tempFarenheit,
          date: new Date()
        };
      }
    ));
  }
}
