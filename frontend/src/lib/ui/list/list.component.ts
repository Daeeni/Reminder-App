import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { ListI } from 'src/lib/data-access/interfaces/listI';
import { BackendService } from 'src/lib/data-access/services/backend.service';
import { CurrentlyViewedListService } from 'src/lib/ui/services/curentlyViewed.service';

@Component({
  selector: 'list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
  providers: [],
})
export class ListComponent implements AfterViewInit {
  @Input() listObject: ListI;
  @Input() selectedOnCreate: boolean;
  @Output() onToViewEvent = new EventEmitter<ListI>();
  @ViewChild('myInput') myInput: ElementRef;
  currentlyViewed: boolean = false;

  constructor(
    private backendService: BackendService,
    private curViewService: CurrentlyViewedListService
  ) {}

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.myInput.nativeElement.focus();
    }
    this.curViewService.notifyOthersObservable$.subscribe((id) => {
      if (id == this.listObject.id) {
        this.currentlyViewed = true;
      } else {
        this.currentlyViewed = false;
      }
    });
  }
  editValue(event: any): void {
    this.listObject.value = event.target.value;
    this.backendService.updateList(this.listObject).subscribe();
  }
  clickToViewerComm(): void {
    this.curViewService.notifyRest(this.listObject.id);
    this.onToViewEvent.emit(this.listObject);
  }
}
