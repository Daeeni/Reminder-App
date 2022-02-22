import { Injectable } from '@angular/core';
import { Subject } from 'rxjs';

@Injectable()
export class CurrentlyViewedListService {
  private notifyOthers = new Subject<number>();
  notifyOthersObservable$ = this.notifyOthers.asObservable();
  constructor() {}
  public notifyRest(id: number) {
    this.notifyOthers.next(id);
  }
}
