import { Component, Input, OnInit } from '@angular/core';
import { BoardI } from 'src/lib/data-access/interfaces/boardI';
import { ItemI } from 'src/lib/data-access/interfaces/itemI';
import { ListI } from 'src/lib/data-access/interfaces/listI';
import { BackendService } from 'src/lib/data-access/services/backend.service';
import { CurrentlyViewedListService } from 'src/lib/ui/services/curentlyViewed.service';

@Component({
  selector: 'board',
  templateUrl: './board.component.html',
  styleUrls: ['./board.component.scss'],
  providers: [],
})
export class BoardComponent implements OnInit {
  @Input() title: string;
  dateToday: string;
  boardObject?: BoardI;
  todayFilter: ListI;
  flaggedFilter: ListI;
  selectedList: ListI;
  curViewedList: ListI;
  itemCounter: number = 0;
  viewFlagged: boolean = false;
  viewToday: boolean = false;

  constructor(
    private backendService: BackendService,
    private curViewService: CurrentlyViewedListService
  ) {}

  ngOnInit(): void {
    var today = new Date();
    var dd = String(today.getDate()).padStart(2, '0');
    var mm = String(today.getMonth() + 1).padStart(2, '0');
    var yyyy = today.getFullYear();
    this.dateToday = yyyy + '-' + mm + '-' + dd;
    this.flaggedFilter = {
      id: -2,
      value: 'Flagged Notes',
      items: [],
    };
    this.todayFilter = {
      id: -1,
      value: "Today's Notes",
      items: [],
    };

    this.backendService.loadBoard().subscribe((board) => {
      this.boardObject = board;
      this.initToday();
      this.initFlagged();
    });
    if (!this.boardObject) {
      this.boardObject = { title: this.title, lists: [] };
    }
  }

  removeItem(id: number, list: ListI) {
    for (var i = 0; i < list.items.length; i++) {
      if (list.items[i].id == id) {
        this.backendService.deleteItem(list.id, id).subscribe();
        list.items.splice(i, 1);
      }
    }
  }
  removeItemFilter(id: number) {
    this.removeItemFilterOnly(id, this.todayFilter);
    this.removeItemFilterOnly(id, this.flaggedFilter);
    var arr = this.boardObject.lists;
    for (let i = 0; i < arr.length; i++) {
      this.removeItem(id, arr[i]);
    }
  }
  removeItemFilterOnly(id: number, list: ListI) {
    for (var i = 0; i < list.items.length; i++) {
      if (list.items[i].id == id) {
        list.items.splice(i, 1);
      }
    }
  }
  searchAndChangeItem(item: ItemI) {
    for (var i = 0; i < this.boardObject.lists.length; i++) {
      for (var x = 0; x < this.boardObject.lists[i].items.length; x++) {
        if (item.id == this.boardObject.lists[i].items[x].id) {
          this.backendService
            .updateItem(this.boardObject.lists[i].id, item)
            .subscribe();
        }
      }
    }
  }
  changeItemFilter(item: ItemI) {
    if (!item.flagged) this.removeItemFilterOnly(item.id, this.flaggedFilter);
    if (item.date != this.dateToday)
      this.removeItemFilterOnly(item.id, this.todayFilter);
    if (item.flagged && !this.flaggedFilter.items.includes(item))
      this.flaggedFilter.items.push(item);
    if (item.date == this.dateToday && !this.todayFilter.items.includes(item))
      this.todayFilter.items.push(item);
  }
  listToViewer(list: ListI): void {
    this.curViewedList = list;
    this.viewFlagged = false;
    this.viewToday = false;
  }
  todayToViewer(): void {
    this.viewToday = true;
    this.viewFlagged = false;
    this.curViewService.notifyRest(-1);
    this.curViewedList = this.todayFilter;
  }
  flaggedToViewer(): void {
    this.viewFlagged = true;
    this.viewToday = false;
    this.curViewService.notifyRest(-1);
    this.curViewedList = this.flaggedFilter;
  }
  createList(input: any): void {
    let list: ListI = {
      id: this.boardObject.lists.length,
      value: '',
      items: [],
    };
    this.selectedList = list;
    this.backendService.createList(this.selectedList).subscribe((listE) => {
      this.selectedList.id = listE.id;
    });
    this.boardObject.lists.push(this.selectedList);
  }
  initToday(): void {
    let z = 0;
    let arr = this.boardObject.lists;
    for (let i = 0; i < arr.length; i++) {
      var curItems = arr[i].items;
      for (; z < curItems.length; z++) {
        if (curItems[z].date == this.dateToday) {
          this.todayFilter.items.push(curItems[z]);
        }
      }
      z = 0;
    }
  }
  initFlagged(): void {
    let z = 0;
    let arr = this.boardObject.lists;

    for (let i = 0; i < arr.length; i++) {
      var curItems = arr[i].items;
      for (; z < curItems.length; z++) {
        if (curItems[z].flagged) {
          this.flaggedFilter.items.push(curItems[z]);
        }
      }
      z = 0;
    }
  }
}
