import { Component } from '@angular/core';
import { OvenTempService } from './oven-temp.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  title = 'OvenTempApp';
  tempCelsius: string = "0.00";
  tempFarenheit: string = "0.00";

  constructor(private ovenTempService: OvenTempService) {

  }

  ngOnInit() {
    this.ovenTempService.msg.subscribe(msg => {
      this.tempCelsius = msg.tempCelsius;
      this.tempFarenheit = msg.tempFarenheit;
    });
  }
}
