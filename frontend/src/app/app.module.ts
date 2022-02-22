import { HttpClientModule } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { BoardComponent } from 'src/lib/ui/board/board.component';
import { BtnCreateComponent } from 'src/lib/ui/btnCreate/btnCreate.component';
import { ItemComponent } from 'src/lib/ui/item/item.component';
import { ListComponent } from 'src/lib/ui/list/list.component';
import { CurrentlyViewedListService } from 'src/lib/ui/services/curentlyViewed.service';
import { ToolbarComponent } from 'src/lib/ui/toolbar/toolbar.component';
import { ViewerComponent } from 'src/lib/ui/viewer/viewer.component';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';

@NgModule({
  declarations: [
    AppComponent,
    ToolbarComponent,
    BoardComponent,
    ListComponent,
    ItemComponent,
    ViewerComponent,
    BtnCreateComponent,
  ],
  imports: [BrowserModule, AppRoutingModule, HttpClientModule],
  providers: [CurrentlyViewedListService],
  bootstrap: [AppComponent],
})
export class AppModule {}
