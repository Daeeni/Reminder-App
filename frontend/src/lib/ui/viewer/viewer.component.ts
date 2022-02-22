import { Component, EventEmitter, Input, Output } from '@angular/core';
import { ItemI } from 'src/lib/data-access/interfaces/itemI';
import { ListI } from 'src/lib/data-access/interfaces/listI';
import { BackendService } from 'src/lib/data-access/services/backend.service';

@Component({
  selector: 'viewer',
  templateUrl: './viewer.component.html',
  styleUrls: ['./viewer.component.scss'],
})
export class ViewerComponent {
  @Input() listObject?: ListI;
  @Input() itemCounter: number;
  @Output() doItemFilterChange = new EventEmitter<ItemI>();
  @Output() doItemSearchAndChange = new EventEmitter<ItemI>();
  @Output() doItemDelete = new EventEmitter<number>();
  selectedItem: ItemI;
  constructor(private backendService: BackendService) {}

  createItem(input: any): void {
    let item: ItemI = {
      id: this.itemCounter++,
      value: '',
      flagged: false,
      date: '',
    };
    this.selectedItem = item;

    this.backendService
      .createItem(this.listObject.id, this.selectedItem)
      .subscribe((itemE) => {
        this.selectedItem.id = itemE.id;
      });

    this.listObject.items.push(this.selectedItem);
  }
  deleteItem(id: number): void {
    this.doItemDelete.emit(id);
  }
  changeItem(item: ItemI): void {
    this.doItemSearchAndChange.emit(item);
    this.doItemFilterChange.emit(item);
  }
}
