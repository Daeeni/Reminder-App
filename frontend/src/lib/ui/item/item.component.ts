import {
  AfterViewInit,
  Component,
  ElementRef,
  EventEmitter,
  Input,
  Output,
  ViewChild,
} from '@angular/core';
import { ItemI } from 'src/lib/data-access/interfaces/itemI';

@Component({
  selector: 'item',
  templateUrl: './item.component.html',
  styleUrls: ['./item.component.scss'],
  providers: [],
})
export class ItemComponent implements AfterViewInit {
  @Input() itemObject: ItemI;
  @Input() selectedOnCreate: boolean;
  @Output() onItemDelete = new EventEmitter<number>();
  @Output() onItemChange = new EventEmitter<ItemI>();
  @ViewChild('myInput') myInput: ElementRef;
  @ViewChild('myDate') myDate: ElementRef;
  elementRef: ElementRef;
  interval;
  delete: boolean = false;
  timeLeft: number = 3;

  ngAfterViewInit(): void {
    if (this.selectedOnCreate) {
      this.myInput.nativeElement.focus();
    }
  }
  editDate(event: any): void {
    this.itemObject.date = event.target.value;
    this.onItemChange.emit(this.itemObject);
  }
  editValue(event: any): void {
    this.itemObject.value = event.target.value;
    this.onItemChange.emit(this.itemObject);
  }
  toggleFlaggedBtn() {
    this.itemObject.flagged = !this.itemObject.flagged;
    this.onItemChange.emit(this.itemObject);
  }
  toggleDeleteBtn() {
    this.delete = !this.delete;
    if (this.delete) {
      this.startTimer();
    } else {
      this.pauseTimer();
    }
  }
  startTimer() {
    this.interval = setInterval(() => {
      if (this.timeLeft > 1) {
        this.timeLeft--;
      } else {
        this.onItemDelete.emit(this.itemObject.id);
        this.pauseTimer();
      }
    }, 1000);
  }
  pauseTimer() {
    clearInterval(this.interval);
    this.timeLeft = 3;
  }
}
