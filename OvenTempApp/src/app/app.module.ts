import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppComponent } from './app.component';
import { OvenTempService } from './oven-temp.service';
import { WebsocketService } from './websocket.service';

@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    BrowserModule
  ],
  providers: [WebsocketService, OvenTempService],
  bootstrap: [AppComponent]
})
export class AppModule { }
